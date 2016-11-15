# PROS skeleton project

Usage with docker:

```bash
docker build -t "docker-pros" -f Dockerfile .
docker run -v `pwd`:/build "docker-pros" sh -c 'make'
```
