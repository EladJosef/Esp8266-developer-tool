<script>
  import { fromEvent } from "file-selector";
  import { createEventDispatcher } from "svelte";
  const dispatch = createEventDispatcher();
  let getFilesFromEvent = fromEvent;
  let fileHover = false;
  let text_click = false;

  function drop_file(event) {
    event.preventDefault();
    fileHover = !fileHover;
    Promise.resolve(getFilesFromEvent(event)).then((drop_file) => {
      if (String(drop_file[0].path).split(".")[1] === "log") {
        send(String(drop_file[0].path));
      }
    });
  }
  function handleDragEnter(e) {
    fileHover = true;
  }

  function handleDragLeave(e) {
    fileHover = false;
    text_click = false;
  }

  function text_hover() {
    text_click = true;
  }

  function text_not_hover() {
    text_click = false;
  }

  function drag_file_click(e) {
    document.getElementById("log_file_input").click();
  }

  function send(path) {
    dispatch("file_has_loaded", [path, true]);
  }
</script>

<div
  id="file_panel"
  on:onchange={drop_file}
  on:dragenter={handleDragEnter}
  on:dragleave={handleDragLeave}
>
  <div class={fileHover ? "hide" : ""} style="position: absolute; left: 50%;">
    <div
      class="middel"
      on:click={drag_file_click}
      on:mouseover={text_hover}
      on:mouseout={text_not_hover}
    >
      Drop log file
    </div>
  </div>
  <input
    type="file"
    class={fileHover || text_click ? "panel-drop-active" : "panel"}
    accept=".log"
    id="log_file_input"
    on:change={drop_file}
  />
</div>

<style>
  .panel {
    width: 80%;
    height: 40vh;
    margin: auto;
    border: 1vh dotted #dddddd;
    background-color: #222831;
    -webkit-app-region: no-drag;
    transition: 0.3s;
    padding-top: 20vh;
    margin-top: 8vh;
    color: transparent;
  }
  .panel::-webkit-file-upload-button {
    visibility: hidden;
  }
  .panel-drop-active::-webkit-file-upload-button {
    visibility: hidden;
  }
  .panel-drop-active,
  .panel:hover {
    width: 75%;
    height: 40vh;
    margin: auto;
    border: 1vh dotted #dddddd;
    background-color: #444f5e;
    -webkit-app-region: no-drag;
    transition: 0.3s;
    padding-top: 20vh;
    margin-top: 8vh;
    cursor: pointer;
    color: transparent;
  }
  .middel {
    position: relative;
    font-family: "Poppins", sans-serif;
    color: #dddddd;
    font-size: 10vh;
    right: 50%;
    margin-top: 28vh;
  }
  .middel:hover {
    cursor: pointer;
  }
  .hide {
    display: none;
  }
</style>
