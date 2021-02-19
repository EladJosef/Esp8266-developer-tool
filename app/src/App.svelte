<script>
  import Notifications from "svelte-notifications";
  import Pannel from "./Pannel.svelte";
  export let address;
  export let debug;
</script>

<Notifications>
  <main>
    <!-- this is main -->
    <Pannel {address} {debug} />
  </main>
</Notifications>

<style>
  main {
    padding: 0;
    margin: 0;
  }
</style>
