class RingBuffer
{
    public:
        RingBuffer(uint16_t length);
        void RingBuffer::reset();
        void RingBuffer::put(char item);
        uint8_t RingBuffer::get();
        bool RingBuffer::isEmpty();
        uint16_t RingBuffer::getSize();
        uint16_t RingBuffer::getLeading();
        uint16_t RingBuffer::getLagging();

    private:
        char *buffer;
        uint16_t size;
        uint16_t leading;
        uint16_t lagging;
        bool empty;
};