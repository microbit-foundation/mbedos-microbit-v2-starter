#include "mbed.h"
#include <stdio.h>

RawSerial pc(P0_6, P1_8);

class ByteBuffer
{
private:
    uint32_t head;
    uint32_t tail;
    const size_t size;
    uint8_t* buffer;
public:
    ByteBuffer(size_t buffer_size): size(buffer_size) {
        head = 0;
        tail = 0;
        buffer = new uint8_t[buffer_size];
    }

    ~ByteBuffer() {
        delete[] buffer;
    }

    bool empty() {
        return head == tail;
    }

    bool full() {
        uint32_t new_tail = tail + 1;
        if (new_tail >= size) {
            new_tail = new_tail - size;
        }
        return head == new_tail;
    }

    void enqueue(uint8_t data) {
        if (full()) {
            error("Queue full\n");
        }
        buffer[tail] = data;
        tail++;
        if (tail >= size) {
            tail -= size;
        }
    }

    uint8_t dequeue() {
        uint8_t data;
        if (empty()) {
            error("Queue empty\n");
        }
        data = buffer[head];
        head++;
        if (head >= size) {
            head = head - size;
        }
        return data;
    }

};

DigitalOut rows[5] = {
    DigitalOut(ROW_1, 0),
    DigitalOut(ROW_2, 0),
    DigitalOut(ROW_3, 0),
    DigitalOut(ROW_4, 0),
    DigitalOut(ROW_5, 0)
};
DigitalOut cols[5] = {
    DigitalOut(COL_1, 1),
    DigitalOut(COL_2, 1),
    DigitalOut(COL_3, 1),
    DigitalOut(COL_4, 1),
    DigitalOut(COL_5, 1)
};

int main()
{
    uint32_t baud;
    uint32_t count;
    uint32_t index;
    uint32_t val;
    uint8_t str[64];
    ByteBuffer buf(1024);
    count = 0;
    index = 0;
    
    int i = 0;
    int j = 0;
    
    rows[0] = 1;
    cols[0] = 0;

    pc.baud(115200);
    pc.printf("{init}");
    while (1) {

        // Enqueue data as it arrives
        while (pc.readable() && !buf.full()) {
            val = pc.getc();
            buf.enqueue(val);
        }

        // Process and send data
        if (!buf.empty() && pc.writeable()) {
            val = buf.dequeue();
            // Check for overflow. Leave space for
            // a null terminating character
            if (index >= sizeof(str) - 1) {
                index = 0;
            }

            // Check for start of frame
            if ('{' == val) {
                index = 0;
            }

            // Check for end of frame
            str[index] = val;
            index++;

            // Check for end of frame
            if ('}' == val && index > 0) {
                str[index] = 0;
                count = sscanf((char*)str, "{baud:%i}", &baud);
            }

            // Echo back character
            pc.putc(val);
            
            if (i == 5) i = 0;
            rows[i] = 1;
            int prev_i = i - 1;
            if (prev_i < 0) prev_i = 4;
            rows[prev_i] = 0;
            if (j == 5) j = 0;
            cols[j] = 0;
            int prev_j = j - 1;
            if (prev_j < 0) prev_j = 4;
            cols[prev_j] = 1;
            j++;
            if (j == 5) i++;

            // Set baud if there is a valid command
            if (count == 1) {
                wait(0.01f);
                pc.baud(baud);
                // Make sure pc has enough time
                // LCP11u35 requires ~0.1us while K20D requires ~0.01us
                wait(0.1f);
                pc.printf("{change}");
                count = 0;
            }
        }
    }
}
