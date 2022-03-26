#ifndef MESSAGE_H
#define MESSAGE_H

struct Message
{
    Message() {}
    uint32_t originator_id;
    uint32_t id;
    uint32_t len;
    char data[8];
};

#endif //