#ifndef FIFO_MODULE_H
#define FIFO_MODULE_H

#include <systemc.h>

// interfaces
class write_if : virtual public sc_interface {
   public:
     virtual void write(char) = 0;
     virtual void reset() = 0;
};

class read_if : virtual public sc_interface {
   public:
     virtual void read(char &) = 0;
     virtual int num_available() = 0;
};

// FIFO Channel
class fifo : public sc_channel, public write_if, public read_if {
   public:
     fifo(sc_module_name name) : sc_channel(name), num_elements(0), first(0) {}

     void write(char c) {
       if (num_elements == max)
         wait(read_event);
       data[(first + num_elements) % max] = c;
       ++num_elements;
       write_event.notify();
     }

     void read(char &c) {
       if (num_elements == 0)
         wait(write_event);
       c = data[first];
       --num_elements;
       first = (first + 1) % max;
       read_event.notify();
     }

     void reset() { num_elements = first = 0; }
     int num_available() { return num_elements; }

   private:
     enum e { max = 10 };
     char data[max];
     int num_elements, first;
     sc_event write_event, read_event;
};

#endif
