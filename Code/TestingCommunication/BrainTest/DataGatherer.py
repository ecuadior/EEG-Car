import serial
import time
import csv
from openpyxl import Workbook

# Set up the serial connection
SERIAL_PORT = 'COM5'  # Change this to match your Arduino's serial port (e.g., '/dev/ttyUSB0' for Linux/Mac)
BAUD_RATE = 115200    # Match this with your Arduino's Serial.begin() baud rate

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    time.sleep(2)  # Allow time for the connection to establish
    print(f"Connected to {SERIAL_PORT}")

    # Create or open a text file to store data
    text_file = open("LN2brainwave_data.txt", "a")  # 'a' for append mode

    # Create an Excel file to store data
    wb = Workbook()
    ws = wb.active
    ws.append(["Time", "Signal Quality", "Attention", "LowBeta"])  # Header row

    while True:
        if ser.in_waiting > 0:
            data = ser.readline().decode('utf-8').strip()  # Read line and remove extra spaces
            print(data)  # Print data for debugging
            
            # Split the received data into components
            parts = data.split(",")  # Assuming values are separated by commas
            if len(parts) >= 3:  # Ensure we have the expected number of values
                signal_quality = parts[0].split(":")[1].strip()
                attention_value = parts[1].split(":")[1].strip()
                lowbeta_value = parts[2].split(":")[1].strip()
                
                timestamp = time.strftime("%Y-%m-%d %H:%M:%S")  # Current timestamp

                # Write to text file
                text_file.write(f"{timestamp}, {signal_quality}, {attention_value}, {lowbeta_value}\n")
                text_file.flush()

                # Write to Excel file
                ws.append([timestamp, signal_quality, attention_value, lowbeta_value])
                wb.save("LN2brainwave_data.xlsx")  # Save Excel file after each entry

except serial.SerialException as e:
    print(f"Error: {e}")

except KeyboardInterrupt:
    print("Program terminated by user.")

finally:
    if 'ser' in locals():
        ser.close()
    if 'text_file' in locals():
        text_file.close()
    if 'wb' in locals():
        wb.save("LN2brainwave_data.xlsx")
    print("Connections closed. Data saved successfully.")
