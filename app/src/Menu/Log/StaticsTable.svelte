<script>
  export let messages;
  function get_statics() {
    return JSON.parse(messages[0]);
  }

  let statistics = get_statics(messages);
</script>

<table>
  <tbody>
    <tr>
      <td class="title">Address</td>
      <td>{statistics.address}</td>
    </tr>
    <tr>
      <td class="title">Number of messages</td>
      <td>{statistics.accept_msg + statistics.send_msg}</td>
    </tr>
    <tr>
      <td class="title">Received messages</td>
      <td>{statistics.send_msg}</td>
    </tr>
    <tr>
      <td class="title">Messages sent</td>
      <td>{statistics.accept_msg}</td>
    </tr>
    <tr>
      <td class="title">Average response time</td>
      <td
        >{statistics.sum_time_between /
          ((statistics.accept_msg + statistics.send_msg) / 2)} ms</td
      >
    </tr>
  </tbody>
</table>

<style>
  table {
    table-layout: fixed;
    border-collapse: collapse;
    height: 72vh;
    width: 94%;
    margin-top: 4vh;
    margin-left: 3vw;
    font-family: "Staatliches", cursive;
  }
  table,
  td {
    border: 1vh solid var(--secondary-color);
    font-size: 5vh;
    background-color: var(--main-color);
    color: var(--secondary-color);
  }
  .title {
    font-size: 5vh;
  }
</style>
