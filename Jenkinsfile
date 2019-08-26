node('') {
    checkout scm
    stage('build-ubuntu') {
       //sh 'docker pull prashantdave/ubuntu-cpp-env:18.04'    
        docker.withRegistry('https://index.docker.io/v1') {
            docker.image('prashantdave/ubuntu-cpp-env:18.04').inside {
                sh 'cd src && docker build -t prashantdave/ubuntu-cpp-fcgi-app:latest -f Dockerfile-ubuntu-cpp-fcgi-app.build .'
            }
        }
    }
}
