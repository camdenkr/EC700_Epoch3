#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <systemd/sd-bus.h>

int main(int argc, char*argv[]) {
        sd_bus_error error = SD_BUS_ERROR_NULL;
        sd_bus_message *reply = NULL;
        const char *canonical;
        sd_bus *bus = NULL;
        uint64_t flags;
        int r;

        r = sd_bus_open_system(&bus);
        if (r < 0) {
                fprintf(stderr, "Failed to open system bus: %s\n", strerror(-r));
                goto finish;
        }

        r = sd_bus_call_method(bus,
                               "org.freedesktop.resolve1",
                               "/org/freedesktop/resolve1",
                               "org.freedesktop.resolve1.Manager",
                               "ResolveHostname",
                               &error,
                               &reply,
                               "isit",
                               0,                                        /* Network interface index where to look (0 means any) */
                               argc >= 2 ? argv[1] : "157.240.14.35",   /* Hostname */
                               AF_UNSPEC,                                /* Which address family to look for */
                               UINT64_C(0));                             /* Input flags parameter */
	if (r < 0) {
               fprintf(stderr, "Failed to resolve hostnme: %s\n", error.message);
                sd_bus_error_free(&error);
                goto finish;
        }
		else{
		printf("Resolved Hostname somehow !! \n");
		}


	//Garbage 
        r = sd_bus_message_enter_container(reply, 'a', "(iiay)");
        if (r < 0)
                goto parse_failure;

        for (;;) {
                char buf[INET6_ADDRSTRLEN];
                int ifindex, family;
                const void *data;
                size_t length;

                r = sd_bus_message_enter_container(reply, 'r', "iiay");
                if (r < 0)
                        goto parse_failure;
                if (r == 0)  /* Reached end of array */
                        break;
                r = sd_bus_message_read(reply, "ii", &ifindex, &family);
                if (r < 0)
                        goto parse_failure;
                r = sd_bus_message_read_array(reply, 'y', &data, &length);
                if (r < 0)
                        goto parse_failure;
                r = sd_bus_message_exit_container(reply);
                if (r < 0)
                        goto parse_failure;

                printf("Found IP address %s on interface %i.\n", inet_ntop(family, data, buf, sizeof(buf)), ifindex);
        }

        r = sd_bus_message_exit_container(reply);
        if (r < 0)
                goto parse_failure;
        r = sd_bus_message_read(reply, "st", &canonical, &flags);
        if (r < 0)
                goto parse_failure;

        printf("Canonical name is %s\n", canonical);
        goto finish;

parse_failure:
        fprintf(stderr, "Parse failure: %s\n", strerror(-r));

finish:
        sd_bus_message_unref(reply);
        sd_bus_flush_close_unref(bus);
        return r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}
