// Load all script snippets on page load
document.addEventListener('DOMContentLoaded', async () => {

    showStartScreen();

    const input = document.getElementById("input");
    const output = document.getElementById("output");

    const commandHistory = [];
    let historyIndex = -1;
    let tempCommand = "";

    input.addEventListener("keydown", function (e) {


        //Sending input if user presses enter
        if (e.key === "Enter" && input.value != "") {

            const command = input.value;

            handleInput(command);

            commandHistory.unshift(command);

            if (commandHistory.length > 50) {
                commandHistory.pop();
            }

            historyIndex = -1;
            tempCommand = "";

            // fetching previous command if user presses up
        } else if (e.key == "ArrowUp") {

            e.preventDefault();

            if (historyIndex < commandHistory.length - 1) {

                if (historyIndex === -1) {
                    tempCommand = input.value;
                }

                historyIndex++;

                input.value = commandHistory[historyIndex];
            }

            // fetching next command if user presses down
        } else if (e.key == "ArrowDown") {

            e.preventDefault();

            if (historyIndex > -1) {

                historyIndex--;

                if (historyIndex === -1) {
                    input.value = tempCommand;
                } else {
                    input.value = commandHistory[historyIndex];
                }
            }

        }

    });

});


//Function to handle inputs
function handleInput(command) {

    switch (command.toLowerCase()) {
        case "clear":
            showStartScreen();
            break;

        case "help":
            output.innerHTML += "<div id=\"user\">> " + command + "<br></div>";
            output.innerHTML += helpCommand;
            break;

        case "github":
            window.open('https://github.com/pierretek/ESP32-LED-Webserver', '_blank').focus();
            break;

        case "shutdown":
            window.top.close();
            break;

        default:
            sendCommand(command);
            output.innerHTML += "<div id=\"user\">> " + command + "<br></div>";
            break;
    }

    input.value = "";
    output.scrollTop = output.scrollHeight;

}

function showStartScreen() {
    output.innerHTML = logoArt +
        "Welcome to the Terminal! Enter your commands below:\n";
}

const logoArt =
    "        _                    _       _          \n" +
    "  _ __ (_) ___ _ __ _ __ ___| |_ ___| | __      \n" +
    " | '_ \\| |/ _ \\ '__| '__/ _ \\ __/ _ \\ |/ /  \n" +
    " | |_) | |  __/ |  | | |  __/ ||  __/   <       \n" +
    " | .__/|_|\\___|_|  |_|  \\___|\\__\\___|_|\\_\\\n" +
    " |_|                                            \n";

const helpCommand =
    "Full List of Commands: \n" +
    "\t<span class=\"command\">led &ltcolor|\"all\"&gt &ltduration&gt &lt\"blink\"|\"pattern\"&gt</span> ➜ controls the specified LEDs for a given duration \n" +
    "\t<span class=\"command\">help</span> ➜ shows this menu \n" +
    "\t<span class=\"command\">clear</span> ➜ clears the terminal \n" +
    "\t<span class=\"command\">shutdown</span> ➜ closes the terminal \n" +
    "\t<span class=\"command\">github</span> ➜ opens this project's github repo \n";

//Function to send commands to the esp32
async function sendCommand(command) {

    try {
        const response = await fetch('/command?cmd=' + encodeURIComponent(command),
            { method: 'GET' });

        const data = await response.text();

        if (response.ok) {
            output.innerHTML += `${data}<br>`;
        } else {
            output.innerHTML += `Error: ${response.status}<br>`;
        }

    } catch (error) {
        output.innerHTML += `Connection failed<br>`;
        console.error('Error:', error);
    }

}


//Function to detect whether the esp32 is connected by periodically sending watchdogs
async function sendWatchDog() {
    const setStatus = (connected) => {
        document.getElementById('status-dot').className = connected ? 'connected' : 'disconnected';
        document.getElementById('status-text').textContent = connected ? 'Connected' : 'Not Connected';
    }

    try {
        await Promise.race([
            fetch('/ping'),
            new Promise((_, reject) => setTimeout(() => reject(), 2000))
        ]);
        setStatus(response.ok);
    } catch {
        setStatus(false);
    }
}

//Checks Connection every 1 seconds
setInterval(sendWatchDog, 1000);
