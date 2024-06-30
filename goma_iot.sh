#!/bin/bash

install_gateway() {
    echo "Installing Gateway..."

    # Check if the script is running on a Raspberry Pi
    IS_RASPBERRY_PI=$(grep -q "Raspberry Pi" /proc/device-tree/model && echo "yes" || echo "no")

    if [ "$IS_RASPBERRY_PI" = "yes" ]; then
        read -p "Do you really want to install Kura for Raspberry Pi? (y/n): " CONFIRM
        if [ "$CONFIRM" = "y" ]; then
            echo "Downloading and installing Kura for Raspberry Pi..."
            wget https://www.eclipse.org/downloads/download.php?file=/kura/releases/5.4.2/kura_5.4.2_raspberry-pi-armhf-nn_installer.deb -O kura_installer.deb
            sudo dpkg -i kura_installer.deb
            sudo apt-get install -f
            echo "Kura installation completed!"
        else
            echo "Kura installation canceled."
        fi
    else
        echo "WARNING: This script is configured to install Kura on a Raspberry Pi. Please ensure you are using a Raspberry Pi before proceeding."
    fi
}

install_cloud() {
    echo "Installing Cloud..."

    # Define URLs e caminhos
    KAPUA_REPO="https://github.com/eclipse/kapua.git"
    LOCAL_COMPOSE_FILE="cloud/docker-compose.yml"
    KAPUA_DIR="kapua"
    DEPLOY_DIR="$KAPUA_DIR/deployment/docker"

    # Baixar o repositório Kapua
    if [ ! -d "$KAPUA_DIR" ]; then
        echo "Cloning Kapua repository..."
        git clone $KAPUA_REPO
    else
        echo "Kapua repository already exists, pulling latest changes..."
        cd $KAPUA_DIR && git pull && cd ..
    fi

    # Substituir o arquivo docker-compose.yml
    if [ -f "$LOCAL_COMPOSE_FILE" ]; then
        echo "Replacing docker-compose.yml with the custom one..."
        cp $LOCAL_COMPOSE_FILE $DEPLOY_DIR/docker-compose.yml
        echo "Replacement done."
    else
        echo "ERROR: Custom docker-compose.yml file not found in $LOCAL_COMPOSE_FILE."
        return 1
    fi

    # Executar o script de implantação
    echo "Running the deployment script..."
    cd $DEPLOY_DIR/unix && ./docker-deploy.sh

    # Verificar se os containers estão no ar
    echo "Checking running Docker containers..."
    docker ps -a
}

start_cloud() {
    echo "Starting Cloud..."

    # Defina o nome do container do broker
    BROKER_CONTAINER="broker"
    
    # Iniciar o container do broker
    echo "Starting broker container..."
    docker start $BROKER_CONTAINER

    # Verificar se o container do broker está rodando
    if [ "$(docker ps -q -f name=$BROKER_CONTAINER)" ]; then
        echo "Broker container started successfully."
    else
        echo "Failed to start broker container. Exiting."
        return 1
    fi

    # Iniciar todos os outros containers
    echo "Starting all other containers..."
    CONTAINERS=$(docker ps -a -q --filter "name!=${BROKER_CONTAINER}")

    for CONTAINER in $CONTAINERS; do
        docker start $CONTAINER
    done

    # Verificar se todos os containers estão rodando
    echo "Checking status of all containers..."
    FAILED_CONTAINERS=$(docker ps -a -q --filter "status=exited")

    if [ -z "$FAILED_CONTAINERS" ]; then
        echo "All containers are running successfully."
    else
        echo "Some containers failed to start. Attempting to restart them..."
        for CONTAINER in $FAILED_CONTAINERS; do
            docker start $CONTAINER
            if [ "$(docker ps -q -f id=$CONTAINER)" ]; then
                echo "Container $CONTAINER restarted successfully."
            else
                echo "Failed to restart container $CONTAINER."
            fi
        done
    fi
}

stop_cloud() {
    echo "Stopping all containers..."

    # Parar todos os containers
    CONTAINERS=$(docker ps -q)

    if [ -n "$CONTAINERS" ]; then
        for CONTAINER in $CONTAINERS; do
            docker stop $CONTAINER
        done
        echo "All containers stopped successfully."
    else
        echo "No running containers to stop."
    fi
}

restart_cloud() {
    echo "Restarting all containers..."

    # Chamar a função de parar containers
    stop_cloud

    # Chamar a função de iniciar containers
    start_cloud

    echo "All containers restarted successfully."
}


status_cloud() {
    echo "Status Cloud:"
    docker ps -as
}

start_gateway() {
    echo "Iniciando Gateway..."
    # Adicione aqui o código para iniciar o gateway
}

stop_gateway() {
    echo "Parando Gateway..."
    # Adicione aqui o código para parar o gateway
}

restart_gateway() {
    echo "Reiniciando Gateway..."
    # Adicione aqui o código para reiniciar o gateway
}

status_gateway() {
    echo "Status do Gateway:"
    # Adicione aqui o código para verificar o status do gateway
}

case "$1" in
    install)
        case "$2" in
            gateway)
                install_gateway
                ;;
            cloud)
                install_cloud
                ;;
            *)
                echo "Usage: $0 install {gateway|cloud}"
                exit 1
                ;;
        esac
        ;;
    cloud)
        case "$2" in
            start)
                start_cloud
                ;;
            stop)
                stop_cloud
                ;;
            restart)
                restart_cloud
                ;;
            status)
                status_cloud
                ;;
            *)
                echo "Usage: $0 cloud {start|stop|restart|status}"
                exit 1
                ;;
        esac
        ;;
    gateway)
        case "$2" in
            start)
                start_gateway
                ;;
            stop)
                stop_gateway
                ;;
            restart)
                restart_gateway
                ;;
            status)
                status_gateway
                ;;
            *)
                echo "Usage: $0 gateway {start|stop|restart|status}"
                exit 1
                ;;
        esac
        ;;
    *)
        echo "Usage: $0 {install|cloud|gateway}"
        exit 1
        ;;
esac