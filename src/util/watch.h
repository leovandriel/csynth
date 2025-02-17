#ifndef CSYNTH_WATCH_H
#define CSYNTH_WATCH_H

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __linux__
#include <sys/inotify.h>
#elif __APPLE__
#include <sys/event.h>
#endif

#define EVENT_BUF_LEN (1024 * (sizeof(struct inotify_event) + 16))

typedef struct
{
#ifdef __linux__
    int fd;
    int wd;
#elif __APPLE__
    int fd;
    int kq;
    struct kevent change;
#endif
} Watch;

int watch_init(Watch *watch, const char *filename)
{
#ifdef __linux__
    watch->fd = inotify_init();
    if (watch->fd < 0)
    {
        return errno;
    }
    int watch->wd = inotify_add_watch(watch->fd, filename, IN_MODIFY);
    if (watch->wd < 0)
    {
        int error = errno ? errno : -1;
        close(watch->fd);
        return error;
    }
#elif __APPLE__
    watch->fd = open(filename, O_RDONLY);
    if (watch->fd < 0)
    {
        return errno;
    }
    watch->kq = kqueue();
    if (watch->kq == -1)
    {
        int error = errno ? errno : -1;
        close(watch->fd);
        return error;
    }
    EV_SET(&watch->change, watch->fd, EVFILT_VNODE, EV_ADD | EV_ENABLE | EV_CLEAR, NOTE_WRITE, 0, NULL);
#endif
    return 0;
}

int watch_change(Watch *watch)
{
#ifdef __linux__
    char buffer[EVENT_BUF_LEN];
    while (1)
    {
        int length = read(watch->fd, buffer, EVENT_BUF_LEN);
        if (length < 0)
        {
            return errno ? errno : -1;
        }
        struct inotify_event *event = (struct inotify_event *)buffer;
        if (event->mask & IN_MODIFY)
        {
            return 0;
        }
    }
#elif __APPLE__
    while (1)
    {
        struct kevent event;
        int nev = kevent(watch->kq, &watch->change, 1, &event, 1, NULL);
        if (nev == -1)
        {
            return errno ? errno : -1;
        }
        else if (nev > 0 && event.fflags & NOTE_WRITE)
        {
            return 0;
        }
    }
#endif
}

void watch_close(Watch *watch)
{
#ifdef __linux__
    inotify_rm_watch(watch->fd, watch->wd);
    close(watch->fd);
#elif __APPLE__
    close(watch->kq);
    close(watch->fd);
#endif
}

#endif // CSYNTH_WATCH_H
