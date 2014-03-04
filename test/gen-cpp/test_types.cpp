/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#include "test_types.h"

namespace test {

const char* KeepAliveReq::ascii_fingerprint = "A1762A7ADE36FC073C7A3B61941FA5BF";
const uint8_t KeepAliveReq::binary_fingerprint[16] = {0xA1,0x76,0x2A,0x7A,0xDE,0x36,0xFC,0x07,0x3C,0x7A,0x3B,0x61,0x94,0x1F,0xA5,0xBF};

uint32_t KeepAliveReq::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->service_id);
          this->__isset.service_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->service_type_id);
          this->__isset.service_type_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->current_load_capacity);
          this->__isset.current_load_capacity = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->req_id);
          this->__isset.req_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->current_timestamp_req);
          this->__isset.current_timestamp_req = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t KeepAliveReq::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("KeepAliveReq");
  xfer += oprot->writeFieldBegin("service_id", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->service_id);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("service_type_id", ::apache::thrift::protocol::T_I16, 2);
  xfer += oprot->writeI16(this->service_type_id);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("current_load_capacity", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->current_load_capacity);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("req_id", ::apache::thrift::protocol::T_I32, 4);
  xfer += oprot->writeI32(this->req_id);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("current_timestamp_req", ::apache::thrift::protocol::T_I64, 5);
  xfer += oprot->writeI64(this->current_timestamp_req);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

const char* KeepAliveRes::ascii_fingerprint = "EA8B51362DF46E243B1C2354930D6C5C";
const uint8_t KeepAliveRes::binary_fingerprint[16] = {0xEA,0x8B,0x51,0x36,0x2D,0xF4,0x6E,0x24,0x3B,0x1C,0x23,0x54,0x93,0x0D,0x6C,0x5C};

uint32_t KeepAliveRes::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I16) {
          xfer += iprot->readI16(this->error_code);
          this->__isset.error_code = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->error_text);
          this->__isset.error_text = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->req_id);
          this->__isset.req_id = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 4:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->current_timestamp_req);
          this->__isset.current_timestamp_req = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 5:
        if (ftype == ::apache::thrift::protocol::T_I64) {
          xfer += iprot->readI64(this->current_time_res);
          this->__isset.current_time_res = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t KeepAliveRes::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("KeepAliveRes");
  xfer += oprot->writeFieldBegin("error_code", ::apache::thrift::protocol::T_I16, 1);
  xfer += oprot->writeI16(this->error_code);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("error_text", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->error_text);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("req_id", ::apache::thrift::protocol::T_I32, 3);
  xfer += oprot->writeI32(this->req_id);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("current_timestamp_req", ::apache::thrift::protocol::T_I64, 4);
  xfer += oprot->writeI64(this->current_timestamp_req);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldBegin("current_time_res", ::apache::thrift::protocol::T_I64, 5);
  xfer += oprot->writeI64(this->current_time_res);
  xfer += oprot->writeFieldEnd();
  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

} // namespace
