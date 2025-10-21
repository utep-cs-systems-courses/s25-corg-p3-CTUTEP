CPU = msp430g2553
CFLAGS = -mmcu=${CPU} -I../h
CC = msp430-elf-gcc
AS = msp430-elf-as
AR = msp430-elf-ar

LIBS = ../lib/libTimer.a

TARGET = blinky-buzzy-toy.elf

SRCS = main.c stateMachine.c led.c buzzer.c switches.c
ASMS = stateAdvance.s

OBJS = $(SRCS:.c=.o) $(ASMS:.s=.o)

all: $(TARGET)

$(TARGET): $(OBJS) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBS)

load: $(TARGET)
	# Use mspdebug to program the board (requires mspdebug installed)
	mspdebug rf2500 "prog $(TARGET)"

clean:
	rm -f $(OBJS) $(TARGET)

.s.o:
	$(AS) $< -o $@