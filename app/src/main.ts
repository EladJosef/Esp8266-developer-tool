import App from './App.svelte';

const app = new App({
	target: document.body,
	props: {
		address: [192, 168, 0, 104, 8500]
	}
});

export default app;