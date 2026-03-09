# Contributing

Thanks for your interest in contributing to this CTF template project!

## Code of Conduct

This project is governed by our [Code of Conduct](CODE_OF_CONDUCT.md). Please read it before contributing.

## How to Contribute

### Reporting Issues

- Check existing issues first to avoid duplicates
- Provide clear descriptions and steps to reproduce
- Include environment details (OS, Docker version, etc.)

### Adding New Templates

Each template should at least include the following files:

```
template-name/
├── docker-compose.yml
├── Dockerfile
├── README.md
```

The image name in `docker-compose.yml` should follow the format `ctf-<template-name>`, for example, `ctf-nc-file` for [nc-file](nc-file/).

Each Dockerfile should be in minimal form, using a base image and installing only necessary dependencies. Avoid including unnecessary files or any cache files in the final image.

### Pull Requests

1. Fork the repository and create your branch from `main`
2. Test your changes with `docker-compose up`
3. Update documentation if needed
4. Write clear commit messages
5. Submit your PR with a description of changes

## Guidelines

- Use lowercase with hyphens for directory names
- Test Docker builds before submitting
- Document exposed ports and configuration options
- Follow standard code formatting conventions

Questions? Open an issue for discussion.
