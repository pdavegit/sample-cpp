node('') {
    checkout scm
    stage('build-ubuntu') {
        docker.withRegistry('https://index.docker.io/v1') {
            docker.image('prashantdave/ubuntu-cpp-env:18.04').inside {
                sh 'make -f Makefile.ubuntu all'
		sh 'make -f Makefile.ubuntu test'
            }
        }
    }
    stage('pull-image') {
       sh 'docker pull prashantdave/alpine-cpp-env:latest'
    }
    stage('build-alpine') {
        docker.withRegistry('https://index.docker.io/v1') {
            docker.image('prashantdave/alpine-cpp-env:latest').inside {
                sh 'make -f Makefile.alpine all'
            }
        }
    }    
}
