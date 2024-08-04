import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
data = pd.read_csv("Assignment 1/matrix_multiplication_runtimes.csv")

# Extract columns
dimensions = data['Dimension']
standard_times = data['Standard']
recursive_times = data['Recursive']
strassen_times = data['Strassen']

# Plot the data
plt.figure(figsize=(10, 6))
plt.plot(dimensions, standard_times, label="Square Matrix Multiplication", marker='o', color='blue')
plt.plot(dimensions, recursive_times, label="Square Matrix Multiplication Recursive", marker='o', color='red')
plt.plot(dimensions, strassen_times, label="Strassen's Algorithm", marker='o', color='green')

# Customize the plot
plt.title('Running Times of Square Matrix Multiplication Algorithms')
plt.xlabel('Dimension')
plt.xticks([64, 96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448, 480, 512])
plt.ylabel('Time (seconds)')
plt.legend()
plt.grid(True)
plt.savefig("Assignment 1/matrix_multiplication_runtimes.png")
plt.show()