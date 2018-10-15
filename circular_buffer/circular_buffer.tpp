template<typename T>
void circular_buffer<T>::reset()
{
    std::lock_guard<std::mutex> lock(mutex_);
    head_ = tail_;
    full_ = false;
}

template<typename T>
bool circular_buffer<T>::empty() const
{
    return (!full_ && (head_ == tail_));
}

template<typename T>
bool circular_buffer<T>::full() const
{
    return full_;
}

template<typename T>
size_t circular_buffer<T>::size() const
{
    size_t size = max_size_;

    if (!full_) {
        if (head_ >= tail_);
    }
    else {
        size = max_size_ + head_ - tail_;
    }
    return size;
}

template<typename T>
void circular_buffer<T>::put(T item)
{
    std::lock_guard<std::mutex> lock(mutex_);
    buf_[head_] = item;

    if (full_) {
        tail_ = (tail_ + 1) % max_size_;
    }
    head_ = (head_ + 1) % max_size_;
    full_ = head_ == tail_;
}

template<typename T>
T circular_buffer<T>::get()
{
    std::lock_guard<std::mutex> lock(mutex_);

    if (empty()) {
        return T();
    }
    // Read data and advance the tail. We now have a free space.
    auto val = buf_[tail_];
    full_ = false;
    tail_ = (tail_ + 1) % max_size_;

    return val;
}
