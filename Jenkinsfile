pipeline {
    agent any
    stages {
        stage('ls') {
            steps {
                sh 'ls'
            }
        }
        stage('Semgrep Scan') {
            steps {
                // Run Semgrep scan
                sh 'semgrep scan . --json > semgrep-results.json'

                // Display the scan results
                sh 'cat semgrep-results.json'
            }
        }
                stage('Grype/Syft Scan') {
            steps {
                // Run Grype scan
                sh 'syft ubuntu'
                sh 'grype ubuntu -o json > grype-results.json'
                // Display the scan results
                sh 'cat grype-results.json'
            }
        }
        stage('Trivy Scan') {
            steps {
                // Run Trivy scan
                sh 'trivy fs .'

                // Display the scan results
                //sh 'cat trivy-results.json'
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
        stage('Cleanup') {
            steps {
                // Remove the scan results files
                sh 'rm semgrep-results.json'
                sh 'rm grype-results.json'
                //sh 'rm syft-results.json'
                sh 'rm gitleaks-results.json'
                //sh 'rm trivy-results.json'
                //sh 'rm kics-results.json'
            }
        }

       
    }
}


