// Copyright (c) 2015-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_KV_H_
#define PIKA_KV_H_

#include "blackwidow/blackwidow.h"

#include "include/pika_command.h"
#include "include/pika_partition.h"


/*
 * kv
 */
class SetCmd : public Cmd {
 public:
  enum SetCondition {kNONE, kNX, kXX, kVX, kEXORPX};
  SetCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag), sec_(0), condition_(kNONE) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);

 private:
  std::string key_;
  std::string value_;
  std::string target_;
  int32_t success_;
  int64_t sec_;
  SetCmd::SetCondition condition_;
  virtual void DoInitial() override;
  virtual void Clear() override {
    sec_ = 0;
    success_ = 0;
    condition_ = kNONE;
  }
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class GetCmd : public Cmd {
 public:
  GetCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  virtual void DoInitial() override;
};

class DelCmd : public Cmd {
 public:
  DelCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
  virtual std::vector<std::string> current_key() const {
    return keys_;
  }

 private:
  std::vector<std::string> keys_;
  virtual void DoInitial() override;
};

class IncrCmd : public Cmd {
 public:
  IncrCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t new_value_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class IncrbyCmd : public Cmd {
 public:
  IncrbyCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t by_, new_value_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class IncrbyfloatCmd : public Cmd {
 public:
  IncrbyfloatCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_, value_, new_value_;
  double by_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class DecrCmd : public Cmd {
 public:
  DecrCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t new_value_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class DecrbyCmd : public Cmd {
 public:
  DecrbyCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t by_, new_value_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class GetsetCmd : public Cmd {
 public:
  GetsetCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  std::string new_value_;
  virtual void DoInitial() override;
};

class AppendCmd : public Cmd {
 public:
  AppendCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  std::string value_;
  virtual void DoInitial() override;
};

class MgetCmd : public Cmd {
 public:
  MgetCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag) {};
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
  virtual std::vector<std::string> current_key() const {
    return keys_;
  }

 private:
  std::vector<std::string> keys_;
  virtual void DoInitial() override;
};

class KeysCmd : public Cmd {
 public:
  KeysCmd(const std::string& name , int arity, uint16_t flag)
      : Cmd(name, arity, flag), type_("all") {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string pattern_;
  std::string type_;
  virtual void DoInitial() override;
  virtual void Clear() {
    type_ = "all";
  }
};

class SetnxCmd : public Cmd {
 public:
  SetnxCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  std::string value_;
  int32_t success_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class SetexCmd : public Cmd {
 public:
  SetexCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t sec_;
  std::string value_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class PsetexCmd : public Cmd {
 public:
  PsetexCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t usec_;
  std::string value_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class DelvxCmd : public Cmd {
 public:
  DelvxCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  std::string value_;
  int32_t success_;
  virtual void DoInitial() override;
};

class MsetCmd : public Cmd {
 public:
  MsetCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    for (auto& kv : kvs_) {
      res.push_back(kv.key);
    }
    return res;
  }
 private:
  std::vector<blackwidow::KeyValue> kvs_;
  virtual void DoInitial() override;
};

class MsetnxCmd : public Cmd {
 public:
  MsetnxCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::vector<blackwidow::KeyValue> kvs_;
  int32_t success_;
  virtual void DoInitial() override;
};

class GetrangeCmd : public Cmd {
 public:
  GetrangeCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t start_;
  int64_t end_;
  virtual void DoInitial() override;
};

class SetrangeCmd : public Cmd {
 public:
  SetrangeCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t offset_;
  std::string value_;
  virtual void DoInitial() override;
};

class StrlenCmd : public Cmd {
 public:
  StrlenCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  virtual void DoInitial() override;
};

class ExistsCmd : public Cmd {
 public:
  ExistsCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
  virtual std::vector<std::string> current_key() const {
    return keys_;
  }

 private:
  std::vector<std::string> keys_;
  virtual void DoInitial() override;
};

class ExpireCmd : public Cmd {
 public:
  ExpireCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t sec_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class PexpireCmd : public Cmd {
 public:
  PexpireCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t msec_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class ExpireatCmd : public Cmd {
 public:
  ExpireatCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t time_stamp_;
  virtual void DoInitial() override;
};

class PexpireatCmd : public Cmd {
 public:
  PexpireatCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  int64_t time_stamp_ms_;
  virtual void DoInitial() override;
  virtual std::string ToBinlog(
      uint32_t exec_time,
      const std::string& server_id,
      uint64_t logic_id,
      uint32_t filenum,
      uint64_t offset) override;
};

class TtlCmd : public Cmd {
 public:
  TtlCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  virtual void DoInitial() override;
};

class PttlCmd : public Cmd {
 public:
  PttlCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  virtual void DoInitial() override;
};

class PersistCmd : public Cmd {
 public:
  PersistCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  virtual void DoInitial() override;
};

class TypeCmd : public Cmd {
 public:
  TypeCmd(const std::string& name, int arity, uint16_t flag)
     : Cmd(name, arity, flag) {}
  virtual std::vector<std::string> current_key() const {
    std::vector<std::string> res;
    res.push_back(key_);
    return res;
  }
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  std::string key_;
  virtual void DoInitial() override;
};

class ScanCmd : public Cmd {
 public:
  ScanCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag), pattern_("*"), count_(10) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  int64_t cursor_;
  std::string pattern_;
  int64_t count_;
  virtual void DoInitial() override;
  virtual void Clear() {
    pattern_ = "*";
    count_ = 10;
  }
};

class ScanxCmd : public Cmd {
 public:
  ScanxCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag), pattern_("*"), count_(10) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  blackwidow::DataType type_;
  std::string start_key_;
  std::string pattern_;
  int64_t count_;
  virtual void DoInitial() override;
  virtual void Clear() {
    pattern_ = "*";
    count_ = 10;
  }
};

class PKSetexAtCmd : public Cmd {
public:
  PKSetexAtCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag), time_stamp_(0) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
private:
  std::string key_;
  std::string value_;
  int64_t time_stamp_;
  virtual void DoInitial() override;
  virtual void Clear() {
    time_stamp_ = 0;
  }
};

class PKScanRangeCmd : public Cmd {
 public:
  PKScanRangeCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag), pattern_("*"), limit_(10), string_with_value(false) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  blackwidow::DataType type_;
  std::string key_start_;
  std::string key_end_;
  std::string pattern_;
  int64_t limit_;
  bool string_with_value;
  virtual void DoInitial() override;
  virtual void Clear() {
    pattern_ = "*";
    limit_ = 10;
    string_with_value = false;
  }
};

class PKRScanRangeCmd : public Cmd {
 public:
  PKRScanRangeCmd(const std::string& name, int arity, uint16_t flag)
      : Cmd(name, arity, flag), pattern_("*"), limit_(10), string_with_value(false) {}
  virtual void Do(std::shared_ptr<Partition> partition = nullptr);
 private:
  blackwidow::DataType type_;
  std::string key_start_;
  std::string key_end_;
  std::string pattern_;
  int64_t limit_;
  bool string_with_value;
  virtual void DoInitial() override;
  virtual void Clear() {
    pattern_ = "*";
    limit_ = 10;
    string_with_value = false;
  }
};
#endif
