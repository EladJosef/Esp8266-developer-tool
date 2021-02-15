const { app, BrowserWindow } = require('electron')
const path = require('path')

app.on('ready', () => {
	window = new BrowserWindow({
		width: 800,
		height: 500,
		frame: false,
		webPreferences: { nodeIntegration: true }
	})

	window.loadFile(`${path.join(__dirname, '/index.html')}`)
})

app.on('window-all-closed', () => app.quit())
