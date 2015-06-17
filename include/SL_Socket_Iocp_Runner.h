#ifndef SOCKETLITE_SOCKET_IOCP_RUNNER_H
#define SOCKETLITE_SOCKET_IOCP_RUNNER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
    #pragma once
#endif
#include "SL_Config.h"
#include "SL_Socket_CommonAPI.h"
#include "SL_Sync_Mutex.h"
#include "SL_Thread_Group.h"
#include "SL_Socket_Runner.h"
#include "SL_Socket_Iocp_Handler.h"

#ifdef SOCKETLITE_OS_WINDOWS

template <class TSyncMutex>
class SL_Socket_Iocp_Runner : public SL_Socket_Runner
{
public:
    SL_Socket_Iocp_Runner(ushort concurrency_thread_num=0)
        : completion_port_(NULL)
        , concurrency_thread_num_(concurrency_thread_num)
        , current_handle_size_(0)
    {
    }

    virtual ~SL_Socket_Iocp_Runner()
    {
        close();
    }

    inline int set_buffer_size(int recv_buffer_size = 65536, int send_buffer_size = 65536)
    {
        return 0;
    }

    int open(int  event_mask = SL_Socket_Handler::READ_EVENT_MASK,
             uint max_size = 100000,
             uint max_timeout_ms = 10,
             uint thread_number = 10,
             int8 handler_close_status = SL_Socket_Handler::STATUS_CLOSE)
    {
        close();
        if (max_size <= 0)
        {
            return -1;
        }
        max_size_ = max_size;
        handler_close_status_ = handler_close_status;

        //������ɶ˿ھ��
        completion_port_ = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, concurrency_thread_num_);
        if (INVALID_HANDLE_VALUE == completion_port_)
        {
            return -2;
        }

        //���������߳���
        work_thread_num_ = thread_number;
        return  thread_group_.start(event_loop_proc, this, thread_number, thread_number);
    }

    int close()
    {
        if (NULL == completion_port_)
        {
            return 0;
        }

        //ʹ�����߳��˳�
        for (int i = 0; i < work_thread_num_; ++i)
        {
            //�����˳���Ϣ
            PostQueuedCompletionStatus(completion_port_, -1, 0, NULL);
        }
        thread_group_.stop();
        thread_group_.join();
        CloseHandle(completion_port_);
        completion_port_ =  NULL;

        return 0;
    }

    inline int add_handle(SL_Socket_Handler *socket_handler, int event_mask) 
    {
        //��socket_handler��������ɶ˿�
        if (NULL == CreateIoCompletionPort((HANDLE)socket_handler->socket_, completion_port_, (ULONG_PTR)socket_handler, 0))
        {
            return -1;
        }
        //Ͷ�ݽ��ղ���
        if (((SL_Socket_Iocp_Handler *)socket_handler)->post_recv() < 0)
        {
            return -2;
        }

        socket_handler->runner_pos_ = 0;
        ++current_handle_size_;

        return 0;
    }

    inline int del_handle(SL_Socket_Handler *socket_handler) 
    { 
        if (socket_handler->runner_pos_ >= 0)
        {
            socket_handler->runner_pos_ = -1;
            --current_handle_size_;

            //������
            int ret = socket_handler->handle_close();
            socket_handler->socket_source_->disconnect(socket_handler);
            if (ret >= 0)
            {
                socket_handler->socket_source_->free_handler(socket_handler);
            }
        }

        return 0;
    }

    inline int remove_handle(SL_Socket_Handler *socket_handler) 
    { 
        if (socket_handler->runner_pos_ >= 0)
        {
            socket_handler->runner_pos_ = -1;
            --current_handle_size_;
        }

        return 0; 
    }

    inline size_t get_handler_size() const
    { 
        return current_handle_size_;
    }

    inline int event_loop(int timeout_ms=1)
    {
        SL_Socket_CommonAPI::util_sleep_ms(timeout_ms);
        return 0;
    }

    inline int event_dispatch()
    {
        return event_loop(1);
    }

    inline int thread_event_loop(int timeout = -1)
    { 
        return 0;
    }

    inline int thread_wait()
    {
        thread_group_.join();
        return 0;
    }

    inline int thread_stop()
    { 
        thread_group_.stop();

        //ʹ�����߳��˳�
        for (int i=0; i<work_thread_num_; ++i)
        {
            //�����˳���Ϣ
            PostQueuedCompletionStatus(completion_port_, -1, 0, NULL);
        }
        return 0;
    }

    static unsigned int WINAPI event_loop_proc(void *arg)
    {
        SL_Socket_Iocp_Runner<TSyncMutex> *runner = (SL_Socket_Iocp_Runner<TSyncMutex> *)arg;
        HANDLE completion_port = runner->completion_port_;

        DWORD   byteTransferred = -1;
        BOOL    success = false;
        SL_Socket_Iocp_Handler *per_handle_data = NULL;
        SL_Socket_Iocp_Handler::PER_IO_DATA *per_io_data = NULL;

        while (runner->thread_group_.get_running())
        {
            success = GetQueuedCompletionStatus(completion_port, &byteTransferred, (LPDWORD)&per_handle_data, (LPOVERLAPPED *)&per_io_data, INFINITE);

            //�˳��źŵ���˳��߳�
            if (-1 == byteTransferred)
            {
                return 1;
            }

            //�ͻ����Ѿ��Ͽ����ӻ������ӳ��ִ���
            if (0 == byteTransferred)
            {
                if (NULL != per_handle_data)
                {
                    per_handle_data->last_errno_  = SL_Socket_Handler::ERROR_CLOSE_PASSIVE;
                    per_handle_data->next_status_ = runner->handler_close_status_;
                    runner->del_handle(per_handle_data);
                }
                continue;
            }

            if ( (!success) || (NULL == per_handle_data) || (NULL == per_io_data) )
            { //�����쳣���
                continue;
            }

            if (per_io_data->oper_type == SL_Socket_Iocp_Handler::RECV_POSTED)
            {//��������

                //��Ϣ����
                per_io_data->data_buffer.data_end(byteTransferred);
                if (per_handle_data->handle_read() >= 0)
                {
                    per_handle_data->post_recv();
                }
                else
                {//С��0��ʾ��Socket���쳣, ����ɾ��
                    per_handle_data->next_status_ = SL_Socket_Handler::STATUS_CLOSE;
                    runner->del_handle(per_handle_data);
                }
            }
        }
        return 0;
    }

private:
    HANDLE          completion_port_;           //��ɶ˿ھ��
    ushort          concurrency_thread_num_;    //���д����߳���
    ushort          work_thread_num_;           //�����߳���

    uint            max_size_;
    uint            current_handle_size_;       //��������(����)
    int8            handler_close_status_;

    TSyncMutex      mutex_;
    SL_Thread_Group thread_group_;
};

#endif

#endif

