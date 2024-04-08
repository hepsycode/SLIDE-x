import json

def access_and_modify(data, path, action, value=None):
  """
  This function accesses a specific node in the JSON data,
  performs an action (add, modify, delete), and optionally sets a new value.

  Args:
      data: The JSON data dictionary.
      path: A list representing the path to the node (e.g., ["ALL", "int8_t"]).
      action: The action to perform (add, modify, delete).
      value: The new value to set (optional, only for add and modify actions).
  """
  current = data
  for key in path[:-1]:
    current = current.get(key)
  if action == "add":
    if not isinstance(current, dict):
      raise ValueError("Cannot add node to non-dictionary object")
    current[path[-1]] = value
  elif action == "modify":
    if path[-1] not in current:
      raise KeyError("Node to modify does not exist")
    current[path[-1]] = value
  elif action == "delete":
    if path[-1] not in current:
      raise KeyError("Node to delete does not exist")
    del current[path[-1]]
  else:
    raise ValueError("Invalid action")

# Load the JSON data
with open('parameters.json', 'r') as f:
  data = json.load(f)

# Example usage:
# Add a new node "int64_t" to "ALL" with size "[4, 64]; 2"
access_and_modify(data, ["ALL", "int16_t"], "add", {"size": "[2, 32]; 2"})
access_and_modify(data, ["ALL", "int16_t"], "add", {"a[size]": "[4, 255]"})

# Modify the size of "uint8_t" in "Leon3" to "[1, 16]; 1"
access_and_modify(data, ["Leon3", "uint8_t"], "modify", {"size": "[2, 32];2"})

# Delete the "long" node from "RiscV"
#access_and_modify(data, ["RiscV", "long"], "delete")

# Save the modified data to a new file (optional)
with open('modified_data.json', 'w') as f:
  json.dump(data, f, indent=4)  # Add indentation for readability

# Print the modified data
print(json.dumps(data, indent=4))