document.addEventListener("DOMContentLoaded", function () {

    const btns = document.querySelectorAll("button");

    const updateState = () => {
        fetch("/led-state")
            .then(res => res.json())
            .then(data => {
                //console.log(data)
                for (let led in data) {
                    let etat = document.querySelector(`#${led}-etat`)
                    if (data[led] === "ON") {
                        etat.style.color = "green"
                    } else etat.style.color = "red"
                }
            })
            .catch(error => console.log(error))
    }

    updateState()
    setInterval(updateState, 5000)


    btns.forEach(function (btn) {
        btn.addEventListener("click", function () {
            const id = this.id
            const data = id === "led1" ? { led1: id } : { led2: id }
            fetch("/led-control", {
                method: "POST",
                headers: {
                    "Content-Type": "application/json"
                },
                body: JSON.stringify(data)
            }).then(res => res.json())
                .then(data => {
                    console.log(data)
                    for (let led in data) {
                        let etat = document.querySelector(`#${led}-etat`)
                        if (data[led] === "ON") {
                            etat.style.color = "green"
                        } else etat.style.color = "red"
                    }
                })
                .catch(error => console.log(error))
        });
    });
});


