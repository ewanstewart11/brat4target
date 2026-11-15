import matplotlib.pyplot as plt
import matplotlib.dates as mdates
from extractvars import parse_logfile
import sys

def plot_combined(log_data, variables_to_plot=None):
    plt.figure(figsize=(10, 5))

    # Plot all variables unless a specific list is provided
    keys = variables_to_plot if variables_to_plot else log_data.keys()

    for var_name in keys:
        if var_name in log_data:
            plt.plot(
                log_data[var_name]["timestamps"],
                log_data[var_name]["values"],
                marker=".",
                label=var_name
            )

    plt.title("Log Variables Over Time")
    plt.xlabel("Time/sec")
    plt.ylabel("Value")
    plt.grid(True, linestyle="--", alpha=0.6)
    plt.legend()

    plt.tight_layout()

    # Save instead of showing interactively
    output_filename = "log_plot.png"
    plt.savefig(output_filename, dpi=300)
    print(f"Plot saved successfully to {output_filename}")

    #plt.show()

# --- Usage ---

# --- Example Usage ---
if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: {} logfile.txt".format(sys.argv[0]))
        exit(1)
        
    log_data = parse_logfile(sys.argv[1])
    
    plot_combined(log_data)
