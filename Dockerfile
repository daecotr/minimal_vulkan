FROM voidlinux/voidlinux

RUN mkdir -p /etc/xbps.d && \
  echo "repository=https://repo-default.voidlinux.org/current" > /etc/xbps.d/00-repository-main.conf
RUN xbps-install -Syu -y xbps
RUN xbps-install -Syu

RUN xbps-install -Sy \
	mesa-vulkan-radeon vulkan-loader-devel \
	cmake make clang pkg-config \
	glfw-devel glm \
	Vulkan-ValidationLayers

RUN xbps-install -Sy bash

WORKDIR /minimal_vulkan

COPY . .

RUN cmake -B build && \
	cmake --build build

CMD ["./build/minimal_vulkan"]
