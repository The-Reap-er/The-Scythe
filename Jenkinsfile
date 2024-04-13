pipeline {
    agent any
    stages {
        stage('ls') {
            steps {
                sh 'ls'
            }
        }
                stage('Grype/Syft Scan') {
            steps {
                // Run Grype scan
                sh 'grype ubuntu -o json > grype-results.json'
                // Display the scan results
                sh 'cat grype-results.json'
            }
        }
        stage('GitLeaks Scan') {
            steps {
                // Run GitLeaks scan
                sh 'gitleaks detect --source . -r gitleaks-results.json'

                // Display the scan results
                sh 'cat gitleaks-results.json'
            }
        }

       
    }
}


