import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file
df = pd.read_csv('bst_results.csv')

# Extract columns from the DataFrame
n_values = df['n']
heights = df['avg_height']
build_times = df['avg_build_time']
destroy_times = df['avg_destroy_time']

# Plot height vs n 
plt.figure(figsize=(10, 6))
plt.plot(n_values, heights, color='lightseagreen')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Average Height')
plt.title('Average Height of BST')
plt.grid(True) 
plt.savefig('bst_average_height.png')
plt.show()

# Plot build/destroy time vs n 
plt.figure(figsize=(10, 6))
plt.plot(n_values, build_times, color = 'purple', label='Average Build Time')
plt.plot(n_values, destroy_times, color = 'darkcyan', label='Average Destroy Time')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Time (microseconds)')
plt.title('Average Time to Build and Destroy BST')
plt.legend()
plt.grid(True)
plt.savefig('bst_build_destroy_time.png')
plt.show()
