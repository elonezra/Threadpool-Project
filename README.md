# Threadpool Encryption Tool

**Threadpool Encryption Tool** is a command-line utility designed to efficiently encode and decode data using a custom encryption algorithm. The tool leverages a thread pool to maximize CPU utilization, making it ideal for multi-core systems.

## Overview

This tool provides a robust solution for handling encryption and decryption of data streams using multi-threading. By utilizing a thread pool, it ensures that the encryption process is parallelized, significantly improving performance on multi-core systems.

### Key Features

- **Thread Pool Implementation**: The tool uses a custom thread pool to manage and execute tasks concurrently, ensuring optimal performance.
- **Encryption & Decryption**: Supports both encryption (`-e`) and decryption (`-d`) modes using a provided shared library.
- **Stream-Based Operation**: Designed to work seamlessly with data streams, allowing for flexible input and output handling via standard input (`stdin`) and standard output (`stdout`).
- **Efficient Performance**: The multi-threaded approach ensures that the encryption algorithm runs faster, especially on multi-core systems.

## Usage

The **Threadpool Encryption Tool** can be used directly from the command line. Below are some examples of how to use it:

### Basic Usage

- **Encryption**:  
  ```bash
  coder <key> -e < input_file > encrypted_file
  ```

- **Decryption**:  
  ```bash
  coder <key> -d < encrypted_file > output_file
  ```

### Piping Example

- Encrypting data from a stream:
  ```bash
  cat input_file | coder <key> -e > encrypted_file
  ```

- Decrypting data from a stream:
  ```bash
  cat encrypted_file | coder <key> -d > output_file
  ```

### Parameters

- `<key>`: The encryption/decryption key.
- `-e`: Flag to specify encryption mode.
- `-d`: Flag to specify decryption mode.

### Note

- The provided encryption algorithm is implemented in a shared library for x86 architecture.
- The encryption algorithm is intentionally designed to be resource-intensive, processing one character every 5ms, with a maximum of 1024 bytes per operation.
- Proper use of multi-threading is essential to achieve optimal performance.

## Performance Considerations

The **Threadpool Encryption Tool** is optimized to utilize as much of the available CPU resources as possible. This ensures that the encryption and decryption processes are executed efficiently, making full use of multi-core processors.



