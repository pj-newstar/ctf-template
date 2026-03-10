# CTF Template

This repository stores template docker sources for CTF challenges.

## Getting Started

You have to have a basic understanding and experience about Linux.

### What is Docker

[Docker](https://www.docker.com/) is a platform that allows you to develop, ship, and run applications in containers. Containers are lightweight, portable, and self-sufficient environments that include everything needed to run an application, such as code, runtime, system tools, libraries, and settings.

### Installing Docker

You need a unix-like environment to run Docker, such as Linux, WSL2 on Windows, or MacOS. Please refer to the [official Docker documentation](https://docs.docker.com/get-docker/) for installation instructions. We'd recommend using the Docker engine with CLI, see [Docker Engine](https://docs.docker.com/engine/) for more details.

You can also refer to [Tsinghua Open Source Mirror for Docker CE](https://mirrors.tuna.tsinghua.edu.cn/help/docker-ce/) if you meet network issues when installing Docker.

### How FLAG Presents

In this project, FLAG is defaultly given by environment variable `FLAG` when the container starts.

Many platforms inject the FLAG by the fixed environment variable. For example, [GZCTF](https://github.com/GZTimeWalker/GZCTF) injects the FLAG by `GZCTF_FLAG`. To fit the variety of CTF platforms, please change the environment variable name to others in both the challenge source and container starting command like the `docker-compose.yml` file.

To present the FLAG in a file, you can refer to [_library/adapter](_library/adapter/).

> [!TIP]
> [_library/adapter](_library/adapter/) can also help you transfer the FLAG from an environment variable to another environment variable.

### How to Use the Templates

In most cases, you can simply run the following command to build the docker image of a template, in its directory:

```bash
docker compose build
```

Or you can run `docker build` command with the provided `Dockerfile`, according to the context definited in the `Dockerfile`.

## Additional Notes

> [!Note]
> The templates in this repository should be treated as examples. The templates only give you references on how to implement a minimal docker source of a simple challenge. Various demands of different challenges may require you to modify the Dockerfile, source code, or even the structure of the whole docker source. Feel free to ask AI assistants for help to fit your needs.

### nc

Most challenges which requires participants using `nc` to visit, are suitable to be implemented applying the templates starting with `nc-`.

If you want to add Proof of Work protection to your existing challenge, you can refer to [nc-file-pow](nc-file-pow/README.md) template. Or see [pj-newstar/proof-of-work](https://github.com/pj-newstar/proof-of-work).

## Questions & Requests

[Open an issue][request_a_template] to request a new template. Please provide as much detail as possible about the desired template, including the type of challenge, expected functionality, and any specific requirements.

If you have any questions or need assistance, feel free to find existing solutions or ask in the [issue][repo_issue] or [discussion](repo_discussion) section. We welcome contributions and are happy to help you!

[request_a_template]: https://github.com/pj-newstar/ctf-template/issues/new?template=template-request.yml
[repo_issue]: https://github.com/pj-newstar/ctf-template/issues
[repo_discussion]: https://github.com/pj-newstar/ctf-template/discussions

## Contributing

Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on how to contribute to this project.

## Code of Conduct

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## License

Copyright (c) Project NewStar & Contributors. All rights reserved.

Licensed under the [MIT License](LICENSE).
