# mp3ME

**mp3ME** is a Linux desktop music player developed in C++20 using SFML 3 for audio playback and graphical rendering, and TagLib for extracting audio metadata.

The project focuses on building a lightweight, locally managed music player while exploring object-oriented programming, data structures, file I/O, and graphical user interface development in modern C++.

## Features

- **Local Music Playback:** Play audio files stored locally without requiring an internet connection or streaming service.
- **Music Queue:** Manage upcoming songs using a queue backed by a C++ `std::deque`.
- **Metadata Extraction:** Use TagLib to retrieve information such as song titles, artists, albums, and release years.
- **Custom Graphical Interface:** Render and interact with the music player through an SFML-based desktop interface.
- **Binary Data Persistence:** Serialize song information to binary files, allowing the application to restore its stored music library between sessions.
- **Music Library Management:** Organize loaded songs and their associated metadata.

## Tech Stack

| Technology | Purpose |
|---|---|
| C++20 | Core application logic |
| SFML 3 | Audio playback, graphics, and window management |
| TagLib | Audio metadata extraction |
| CMake | Build configuration and dependency management |
| C++ Standard Library | Containers, file I/O, filesystem operations, and memory management |

## Building from Source

### Prerequisites

- A C++20-compatible compiler
- CMake 3.16 or newer
- SFML 3.0.2
- TagLib 2.1.1

The project currently uses locally included SFML and TagLib dependencies.

### Build Instructions

Clone the repository:

```bash
git clone https://github.com/SwaggyEmi/mp3ME.git
cd mp3ME
```

Configure the project with CMake:

```bash
cd build
cmake ..
```

Compile the application:

```bash
make
```

Run the generated executable from the build output directory.

*Note: Build requirements and executable locations may vary depending on the operating system and compiler.*

## Architecture

mp3ME separates music data, library management, and playback functionality into different components.

### Song

Represents an individual audio file and its associated metadata.

Information tracked includes:

- File name and path information
- Song title
- Artist
- Album
- Release year
- Play count

### Database

Manages the application's collection of songs, including loading and storing music information.

The application uses binary file operations to preserve library data between sessions.

### Playback and Queue Management

SFML handles audio playback, while the application manages the order of upcoming songs using a `std::deque`.

This approach allows efficient insertion and removal of songs while maintaining an ordered playback queue.

## Technical Highlights

**Custom Binary Serialization**

Instead of relying on an external database management system, mp3ME uses binary file serialization to preserve music library information.

This involves writing and reading structured data, including variable-length strings, using C++ file streams.

**Memory Management**

The project incorporates modern C++ memory management techniques, including smart pointers, to manage dynamically allocated objects and ownership.

**Audio Metadata Integration**

TagLib extracts metadata from local audio files, reducing reliance on manually entered song information.

**Custom UI Development**

The interface is built using SFML rather than a traditional desktop GUI toolkit, providing direct control over rendering and user interactions.

## Planned Improvements

mp3ME is an ongoing personal project. Future improvements include:

- Redesigned, multi-page graphical interface
- Improved navigation and scrolling
- Drag-and-drop audio file importing
- Native file selection dialogs
- Music library refresh functionality
- Expanded playback statistics and play-count tracking
- Improved library organization and search

## Project Goals

The primary goal of mp3ME is to explore desktop application development using modern C++ while applying concepts such as:

- Object-oriented design
- Data structures and algorithms
- Dynamic memory management
- File systems and binary serialization
- Third-party library integration
- Event-driven graphical interfaces

The project also serves as an opportunity to develop and maintain a larger C++ codebase beyond small academic programming assignments.

## License

No license has been specified yet.