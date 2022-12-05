HEADER_DIR = ./include/
SOURCE_DIR = ./src/


PROJECT_NAME = SourceTil
UNITTESTS_NAME = SourceTil_unittest
MOCKTESTS_NAME = SourceTil_mocktest

.PHONY: all clean cleam-dist test-debug test-release build-debug build-release

all: test-debug test-release

build-debug:
	@cmake -B build_debug -DCMAKE_BUILD_TYPE=Debug

build-release:
	@cmake -B build_release -DCMAKE_BUILD_TYPE=Release


test-debug: build-debug
	@cd build_debug && make
	@./build_debug/test/${UNITTESTS_NAME}
	@./build_debug/test/mocks/${MOCKTESTS_NAME}

test-release: build-release
	@cd build_release && make
	@./build_release/test/${UNITTESTS_NAME}

service-start-debug: build-debug
	@cd ./build_debug && ./${PROJECT_NAME}

service-start-release: build-release
	@cd ./build_release && ./${PROJECT_NAME}

clean-impl-%:
	cd build_$* && make clean

lint:
	clang-tidy $(HEADER_DIR)* $(SOURCE_DIR)* --config= -- -std=c++17 -I$(HEADER_DIR)

format:
	clang-format --config= -i $(HEADER_DIR)* $(SOURCE_DIR)*

clean-dist:
	@rm -rf build_*

.PHONY: docker-cmake-debug docker-build-debug docker-test-debug docker-clean-debug docker-cmake-release docker-build-release docker-test-release docker-clean-release docker-install docker-install-debug docker-start-service-debug docker-start-service docker-clean-data

docker-start-service:
	@docker-compose run -p 8080:8080 make -- --debug-start-in-docker

docker-start-service-debug:
	@docker-compose run -p 8080:8080 make -- --debug-start-in-docker-debug

docker-impl-%:
	docker-compose run make $*

docker-cmake-debug: docker-impl-cmake-debug
docker-cmake-release: docker-impl-cmake-release

docker-build-debug: docker-impl-build-debug
docker-build-release: docker-impl-build-release

docker-test-debug: docker-impl-test-debug
docker-test-release: docker-impl-test-release

docker-clean-debug: docker-impl-clean-debug
docker-clean-release: docker-impl-clean-release

docker-install: docker-impl-install
docker-install-debug: docker-impl-install-debug