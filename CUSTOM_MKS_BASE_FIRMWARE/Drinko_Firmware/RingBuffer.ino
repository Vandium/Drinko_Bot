RingBuffer::RingBuffer(uint16_t length)
{
    size = length;
    buffer = malloc(size);
    leading = 0;
    lagging = 0;
    empty = true;
}

void RingBuffer::reset()
{
    leading = 0;
    lagging = 0;

    empty = true;
}

void RingBuffer::put(char item)
{
    if(lagging == leading)
    {
      lagging++;
      lagging %= size;
    }
  
    buffer[leading++] = item;
    leading %= size;

    empty = false;
}

uint8_t RingBuffer::get()
{
    if(empty){
        return 0;   //If the buffer is empty return 0
    }
    else{
        uint8_t item = buffer[lagging++];   //Return the oldest value and increment the lagging pointer
        lagging %= size;
        empty = lagging == leading; //Set the flag in indicating there's no more data
        return item;
    }
}

bool RingBuffer::isEmpty()
{
    return empty;
}

uint16_t RingBuffer::getSize()
{
    return size;
}

uint16_t RingBuffer::getLeading()
{
    return leading;
}

uint16_t RingBuffer::getLagging()
{
    return lagging;
}
