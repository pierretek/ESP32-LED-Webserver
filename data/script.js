document.addEventListener('DOMContentLoaded', function () {
    
    const button1 = document.getElementById('button1');
    const button2 = document.getElementById('button2');
    const button3 = document.getElementById('button3');
    const button4 = document.getElementById('button4');
    const status = document.getElementById('status');
    
    // Single send function that handles different commands based on button ID
    async function sendCommand(buttonId) {
        let command;
        
        // Switch statement to determine which command to send
        switch(buttonId) {
            case 'button1':
                command = 'white';
                break;
            case 'button2':
                command = 'green';
                break;
            case 'button3':
                command = 'red';
                break;
            case 'button4':
                command = 'blue';
                break;
            default:
                command = 'unknown';
        }
        
        status.textContent = `Sending command: ${command}...`;
        
        try {
            const response = await fetch('/command?cmd=' + command, {
                method: 'POST'
            });
            
            if (response.ok) {
                const data = await response.text();
                status.textContent = `Response: ${data}`;
            } else {
                status.textContent = 'Error: ' + response.status;
            }
        } catch (error) {
            status.textContent = 'Connection failed';
            console.error('Error:', error);
        }
    }
    
    // Attach event listeners to all buttons
    button1.addEventListener('click', () => sendCommand('button1'));
    button2.addEventListener('click', () => sendCommand('button2'));
    button3.addEventListener('click', () => sendCommand('button3'));
    button4.addEventListener('click', () => sendCommand('button4'));
});
