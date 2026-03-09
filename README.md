# CTF Template

This repository stores template docker sources for CTF challenges.

## Description

> [!Note]
> The templates in this repository should be treated as examples. The templates only give you references on how to implement a minimal docker source of a simple challenge. Various demands of different challenges may require you to modify the Dockerfile, source code, or even the structure of the whole docker source.

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
