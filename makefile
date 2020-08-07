# -
# Setup test requirements
# -

test-setup:
	cd test
	sampctl package ensure

# -
# Run Tests
# -

test-native:
	sampctl package build
	cd test && sampctl package run

test-container:
	sampctl package build
	cd test && sampctl package run --container

# -
# Build inside container
# -

build-container:
	rm -rf build
	docker build -t aktah/cec-build .
	docker run -v $(shell pwd)/test/plugins:/root/test/plugins aktah/cec-build

# this make target is only run inside the container
build-inside:
	cd build && cmake .. && make
