<script>
  import Pannel from "./Pannel.svelte";
  export let address;
  export let debug;
</script>

<main>
  <Pannel {address} {debug} />
</main>

<style>
  main {
    padding: 0;
    margin: 0;
  }
</style>
