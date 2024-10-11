import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

# Load the data from CSV
data = pd.read_csv("Assignment 3/part_A_1_expanded.csv")

# Convert the execution time to numeric for better plotting
data['Execution time'] = pd.to_numeric(data['Execution time'], errors='coerce')

# Set up the figure
plt.figure(figsize=(14, 10))

# Plot 1: Execution Time vs. Number of Operations (for different number of elements)
plt.subplot(2, 1, 1)
for key, grp in data.groupby('Number of elements'):
    plt.plot(grp['Number of operations'], grp['Execution time'], label=f'Elements: {key}')

plt.title('Execution Time vs. Number of Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Execution Time (seconds)')
plt.legend(title='Number of Elements')
plt.grid()
plt.yscale('log')  # Use logarithmic scale for better visibility
plt.tight_layout()

# Plot 2: Execution Time vs. Number of Elements (for a fixed number of operations)
plt.subplot(2, 1, 2)
for key, grp in data.groupby('Number of operations'):
    plt.plot(grp['Number of elements'], grp['Execution time'], label=f'Operations: {key}')

plt.title('Execution Time vs. Number of Elements')
plt.xlabel('Number of Elements')
plt.ylabel('Execution Time (seconds)')
plt.legend(title='Number of Operations')
plt.grid()
plt.yscale('log')  # Use logarithmic scale for better visibility
plt.tight_layout()

# Show the plots
plt.show()

# Heatmap of Execution Time
pivot_table = data.pivot("Number of elements", "Number of operations", "Execution time")
plt.figure(figsize=(12, 8))
sns.heatmap(pivot_table, annot=True, fmt=".2g", cmap="YlGnBu", cbar_kws={'label': 'Execution Time (seconds)'})
plt.title('Heatmap of Execution Time by Number of Elements and Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Number of Elements')
plt.show()
