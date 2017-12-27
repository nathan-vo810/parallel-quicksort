import matplotlib.pyplot as plt
import os

time_serial = "time_serial.txt"
time_parallel = "time_parallel.txt"

def read_file(file_name):
	with open(file_name, 'r') as file:
		size = []
		time = []
		for line in file:
			data = line.split(",")
			size.append(data[0])
			time.append(data[1])
	return size,time

size_serial,time_serial = read_file(time_serial)
size_parallel,time_parallel = read_file(time_parallel)

plt.plot(size_serial,time_serial,marker ='o',linestyle="--")
plt.plot(size_parallel,time_parallel,marker ='o', linestyle="--")
plt.legend(["Serial Time","Parallel Time"])
plt.xlabel("Array size")
plt.ylabel("Execution time")
plt.show()


