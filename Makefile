/**
* @file makefile
* @description Makefile dosyası, projenin otomatik olarak derlenmesini sağlayan komutları içerir.
* @assignment 1. Ödev
* @date 23 Aralık 2024
* @author Sema Nur ÖZGEN - semanur.ozgen@stu.fsm.edu.tr
*/

# Derleyici ve bayraklar
CC = gcc
CFLAGS = -Wall -Wextra -g

# Hedef dosya
TARGET = program

# Kaynak dosyalar ve header dosyalar
SRC = main.c
OBJ = $(SRC:.c=.o)

# Varsayılan hedef
all: $(TARGET)

# Programın oluşturulması
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# .o dosyalarının oluşturulması
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Temizleme komutu
clean:
	rm -f $(OBJ) $(TARGET)

# Çalıştırma komutu
run: $(TARGET)
	./$(TARGET) birim.txt calisan.txt
	