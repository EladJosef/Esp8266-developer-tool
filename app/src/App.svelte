<script>
  import Pannel from "./Pannel.svelte";
  export let address;
</script>

<main>
  <Pannel {address} />
</main>

<style>
  main {
    padding: 0;
    margin: 0;
  }
</style>
