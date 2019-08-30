node('') {
    checkout scm
    stage('build-ubuntu') {
        docker.build("prashantdave/ubuntu-cpp-fcgi-app:latest", "src")
    }
}
