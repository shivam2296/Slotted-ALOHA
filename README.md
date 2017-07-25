# Slotted-ALOHA
PROGRAM FOR SIMULATING SLOTTED ALOHA TECHNIQUE
  
   Author: Shivam Prasad (prasadshivam2296@gmail.com)
   
   Date:   25th July 2017
   
   Description: This program simulates the SLOTTED-ALOHA technique for sending packets.
   
   Throughput:         The maximum throughput is 1/e frames per frame-time (reached when G = 1), which is approximately 0.368 frames per frame-time, or 36.8%.
  
   Usage: Slotted ALOHA is used in low-data-rate tactical satellite communications networks by military forces,
          in subscriber-based satellite communications networks, mobile telephony call setup, set-top box communications and in the contactless RFID technologies.
  
  
   Input: The program assumes that senders are spread randomly on a maze of size n X m.
   
          The senders have a random range lying in between a min and max value.
          
          Only those senders will communicate whose range is greater than their distance. These Senders are printed.
          
          
          Now, for Slotted ALOHA, input
          
          -> Kmax(The max number of attempts by a sender to send a packet).
          
          -> Tp(Time-out peroid, the number of slots a sender has to wait after a collision).
          
          For the simulator, enter the number of time slots.
          
          Now, the simulator describes the activity at each time slot.
          
          Finally, the total number of packets and the number of successful packets transmitted are displayed.
