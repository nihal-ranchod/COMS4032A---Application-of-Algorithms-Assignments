import pandas as pd
import matplotlib.pyplot as plt

# Part A Plots
df_bst = pd.read_csv('bst_results.csv')

# Extract columns from the DataFrame
bst_n_values = df_bst['n']
bst_heights = df_bst['avg_height']
bst_build_times = df_bst['avg_build_time']
bst_destroy_times = df_bst['avg_destroy_time']

# Plot height vs n 
plt.figure(figsize=(10, 6))
plt.plot(bst_n_values, bst_heights, color='lightseagreen')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Average Height')
plt.title('Average Height of BST')
plt.grid(True) 
plt.savefig('Plots/bst_average_height.png')
plt.show()

# Plot build/destroy time vs n 
plt.figure(figsize=(10, 6))
plt.plot(bst_n_values, bst_build_times, color = 'purple', label='Average Build Time')
plt.plot(bst_n_values, bst_destroy_times, color = 'darkcyan', label='Average Destroy Time')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Time (microseconds)')
plt.title('Average Time to Build and Destroy BST')
plt.legend()
plt.grid(True)
plt.savefig('Plots/bst_build_destroy_time.png')
plt.show()


# -------------------------------------------------------------------------------------
# Part B Plots
df_ost = pd.read_csv('ost_results.csv')

# Extract columns from the DataFrame
ost_n_values = df_ost['n']
ost_heights = df_ost['avg_height']
ost_build_times = df_ost['avg_build_time']
ost_destroy_times = df_ost['avg_destroy_time']

# Plot height vs n 
plt.figure(figsize=(10, 6))
plt.plot(ost_n_values, ost_heights, color='lightseagreen')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Average Height')
plt.title('Average Height of OST')
plt.grid(True) 
plt.savefig('Plots/ost_average_height.png')
plt.show()

# Plot build/destroy time vs n 
plt.figure(figsize=(10, 6))
plt.plot(ost_n_values, ost_build_times, color = 'purple', label='Average Build Time')
plt.plot(ost_n_values, ost_destroy_times, color = 'darkcyan', label='Average Destroy Time')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Time (microseconds)')
plt.title('Average Time to Build and Destroy OST')
plt.legend()
plt.grid(True)
plt.savefig('Plots/ost_build_destroy_time.png')
plt.show()


#-------------------------------------------------------------------------------------
# Combined Plots
# Plot BST/OST height vs n
plt.figure(figsize=(10, 6))
plt.plot(bst_n_values, bst_heights, color='purple', label='BST Height')
plt.plot(ost_n_values, ost_heights, color='blue', label='OST Height')
plt.xlabel('Number of Keys (n)')
plt.ylabel('Average Height')
plt.title('Average Height of BST vs. OST')
plt.legend()
plt.grid(True)
plt.savefig('Plots/bst_ost_average_height.png')
plt.show()

# Plot BST/OST build/destroy time vs n
plt.figure(figsize=(10, 6))
plt.plot(bst_n_values, bst_build_times, color='purple', label='BST Build Time')
plt.plot(bst_n_values, bst_destroy_times, color='darkcyan', label='BST Destroy Time')

# Plot OST build/destroy time vs n 
plt.plot(ost_n_values, ost_build_times, color='blue', label='OST Build Time')
plt.plot(ost_n_values, ost_destroy_times, color='red', label='OST Destroy Time')

plt.xlabel('Number of Keys (n)')
plt.ylabel('Time (microseconds)')
plt.title('Average Time to Build and Destroy BST vs. OST')
plt.legend()
plt.grid(True)
plt.savefig('Plots/bst_ost_build_destroy_time.png')
plt.show()