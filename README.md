# 🗣️ Minitalk

This project challenges you to build a messaging program, where two processes (a client and a server) communicate via signals.

## 🚀 Features

- Enables communication between a client and server using UNIX signals.
- Implements message transmission using only `SIGUSR1` and `SIGUSR2` signals.
- Efficient and robust signal handling.
- The bonus part also includes:
    - Support for unicode characters.
    - A message sent from server to client, when the message from client is successfully received.

## 🛠️ Technologies Used

- **C Programming Language**
- **UNIX Signals**

## 📥 Installation (mandatory)

To run Minitalk on your local machine, follow these steps:

1. **Clone the Repository**:
    ```bash
    git clone https://github.com/luisneves10/minitalk.git
    ```
2. **Navigate to the Project Directory**:
    ```bash
    cd minitalk
    ```
3. **Compile the Code**:
    ```bash
    make
    ```
4. **Run the Program**:
    First, start the server:
    ```bash
    ./server
    ```
    Then, in another terminal, run the client to send a message:
    ```bash
    ./client <server-pid> "Your message"
    ```
## 📥 Installation (bonus)

3. **Compile the Code**:
    ```bash
    make bonus
    ```
4. **Run the Program**:
    First, start the server:
    ```bash
    ./server_bonus
    ```
    Then, in another terminal, run the client to send a message:
    ```bash
    ./client_bonus <server-pid> "Your message"
    ```

## 📚 Learning Experience

- **Signal Handling:** This project enhanced my understanding of UNIX signals, how they work, and how to handle them in a C program.
- **Interprocess Communication:** I learned how to implement a simple form of communication between two independent processes.
