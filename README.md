# JSON Validator CLI Tool

The `json` tool is a command-line interface (CLI) utility designed to validate JSON data. It supports both direct input of JSON strings and parsing JSON data from files. The tool is built using C++ and utilizes a JSON parser for validation.

## Table of Contents

- [Installation](#installation)
- [Usage](#usage)
- [Options](#options)
- [Examples](#examples)
- [Testing](#testing)
- [Contributing](#contributing)
- [License](#license)

## Installation

No installation is required. Simply compile the provided C++ code and obtain the executable `json` file for your platform.

## Usage

```bash
json [OPTIONS] string/file
```

- **string/file**: The JSON data to be validated. It can be provided as a string or read from a file.

## Options

```bash
- -h, --help: Display help information and exit.
- -f, --file FILE_PATH: Path to the JSON file.
- -s, --string JSON_STRING: JSON string (default).
```

## Examples

1. Validate JSON data provided as a string:

```bash
json -s '{"key": "value", "array": [1, 2, 3]}'
```

2. Validate JSON data from a file:

```bash
json -f path/to/json/file.json
```

3. Display help information:

```bash
json --help
```

## Testing

To run the test suite for the JSON parser, use the following command:

```bash
json -t
```

This will execute the predefined test cases and report the results.

## Contributing

Contributions are welcome! Please follow the [contribution guidelines](CONTRIBUTING.md).

## License

This project is licensed under the [MIT License](LICENSE).
