template <typename Type> class GR_integrate_and_dump {
public:
  GR_integrate_and_dump() {}

  void reset() {
    data_ = 0;
    cnt_ = 0;
  }

  bool put(Type data) {
    ++cnt_;
    data_ += data;
    if (cnt_ >= size_) {
      out_ = data_ / size_;
      reset();
      return 1;
    }
    return 0;
  }

  Type get() { return out_; }

  void set_interval(int size, bool reset = 1) {
    if (reset) {
      this->reset();
    }
    size_ = size;
  }
  
  Type get_interval() {
    return size_;
  }

private:
  int cnt_ = 0;
  int size_ = 10;
  Type data_ = 0;
  Type out_ = 0;
};
