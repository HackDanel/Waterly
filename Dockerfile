FROM debian:12

# Устанавливаем все зависимости для Qt и GUI
RUN apt-get update && apt-get install -y \
    build-essential \
    qtbase5-dev \
    qttools5-dev \
    qttools5-dev-tools \
    libqt5widgets5 \
    libqt5gui5 \
    libqt5core5a \
    qtcreator \
    cmake \
    git \
    libx11-6 \
    libxss1 \
    libxrandr2 \
    libasound2 \
    libxi6 \
    libxtst6 \
    libgl1-mesa-glx \
    libfontconfig1 \
    libfreetype6 \
    libxrender1 \
    libxext6 \
    libxfixes3 \
    libxi6 \
    libxkbcommon-x11-0 \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app
COPY . .

RUN mkdir build && cd build && \
    qmake ../*.pro && \
    make -j$(nproc)

CMD ["./build/WaterTracker"]
