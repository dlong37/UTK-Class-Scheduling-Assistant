function deleteSchedule(scheduleId) {
    fetch('/delete-schedule', {
        method: 'POST',
        body: JSON.stringify({ scheduleId: scheduleId})
    }).then((_res) => {
        window.location.href = "/main";
    })
}