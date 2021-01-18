import App from './App.svelte';

const app = new App({
	target: document.body,
	props: {
		address: [127, 0, 0, 1, 8000]
	}
});

export default app;