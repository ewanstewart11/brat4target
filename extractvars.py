import numpy as np
from collections import defaultdict

def parse_logfile(filepath):
    # Store lists of timestamps and values mapped by variable name
    raw_data = defaultdict(lambda: {"timestamps": [], "values": []})

    with open(filepath, "r", encoding="utf-8") as file:
        for line_num, line in enumerate(file, start=1):
            line = line.strip()
            
            # Only process lines ending with the <<<VAR marker
            if not line.endswith("<<<VAR"):
                continue
            
            # Remove the '<<<VAR' suffix
            clean_line = line[:-6]
            
            # Split by tab (falls back to whitespace if tabs were converted to spaces)
            parts = clean_line.split("\t")
            if len(parts) != 3:
                parts = clean_line.split()
                
            if len(parts) != 3:
                print(f"Skipping malformed line {line_num}: {line}")
                continue
                
            timestamp_str, var_name, val_str = parts
            
            dt = float(timestamp_str)/1000
            val = float(val_str)

            raw_data[var_name]["timestamps"].append(dt)
            raw_data[var_name]["values"].append(val)

    # Convert the collected lists into mapped NumPy arrays
    mapped_arrays = {}
    for var_name, content in raw_data.items():
        mapped_arrays[var_name] = {
            "timestamps": np.array(content["timestamps"], dtype=np.float64),
            "values": np.array(content["values"], dtype=np.float64)
        }

    # Write the data as a tsv
    with open("log_data.tsv", "w") as f:
        for var_name, content in raw_data.items():
            # Write each timestamp and value pair for this variable
            for dt, val in zip(content["timestamps"], content["values"]):
                f.write(f"{dt}\t{var_name}\t{val}\n")

    return mapped_arrays
