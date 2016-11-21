# Starstruck PROS project

Usage with docker:

```bash
docker build -t "docker-pros" -f Dockerfile .
docker run -v `pwd`:/build "docker-pros" sh -c 'make'
```

Usage with docker-compose:

```bash
# Start containers
docker-compose up -d
docker attach pros_starstruck_1
# Stop containers
docker-compose stop
```

#### Documentation

* [PROS API](http://pros.cs.purdue.edu/api/)
