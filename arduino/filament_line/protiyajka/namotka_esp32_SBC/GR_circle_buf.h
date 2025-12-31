template <typename Type> class GR_circle_buf {
public:
  GR_circle_buf(size_t size = 32) {
    buf_.resize(size);
    size_ = size;
  }

  void write(Type data) {
    size_t next_wr = wr_point_ + 1;
    if (next_wr >= size_) {
      next_wr = 0;
    }
    buf_[next_wr] = data;
    wr_point_ = next_wr;
  }

  std::pair<Type, bool> read() {
    if (rd_point_ != wr_point_) {
      rd_point_ = rd_point_ + 1;
      if (rd_point_ >= size_) {
        rd_point_ = 0;
      }
      return std::make_pair(buf_[rd_point_], true);
    } else {
      return std::make_pair(buf_[rd_point_], false);
    }
  }
  std::pair<Type, bool> read_silent() {

  }

  bool is_readable() { return (rd_point_ != wr_point_); }

private:
  size_t size_;
  std::vector<Type> buf_;
  volatile size_t rd_point_ = 0;
  volatile size_t wr_point_ = 0;
};