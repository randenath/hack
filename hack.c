#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
 
// ─── ANSI Colors ───────────────────────────────────────────────────────────────
#define GREEN       "\033[0;32m"
#define GREEN_BOLD  "\033[1;32m"
#define YELLOW      "\033[1;33m"
#define RED         "\033[0;31m"
#define RED_BOLD    "\033[1;31m"
#define RESET       "\033[0m"
 
// ─── Message Pools ─────────────────────────────────────────────────────────────
const char *status_msgs[] = {
    "ACCESSING MAINFRAME...",
    "DECRYPTING PAYLOAD...",
    "BYPASSING FIREWALL...",
    "OVERRIDE ACCEPTED...",
    "ESTABLISHING TUNNEL...",
    "ROOT ACCESS GRANTED",
    "ENCRYPTING EXFILTRATED DATA...",
    "WIPING LOGS...",
    "PROXY CHAIN ESTABLISHED [12 NODES]",
};
#define STATUS_COUNT 10
 
const char *alert_msgs[] = {
    "WARNING: INTRUSION COUNTERMEASURES ACTIVE",
    "ALERT: ANOMALOUS TRAFFIC DETECTED",
    "CRITICAL: FIREWALL BREACH LOGGED",
    "WARNING: HONEYPOT DETECTED - AVOIDING...",
};
#define ALERT_COUNT 4

const char *file_paths[] = {
    "/etc/shadow",
    "/var/log/auth.log",
    "/root/.ssh/id_rsa",
    "/home/admin/secrets.txt",
    "/opt/database/users.db",
    "/etc/passwd",
};
#define FILE_COUNT 6

// ─── Signal Handler ────────────────────────────────────────────────────────────
void handle_sigint(int sig) {
    (void)sig;
    printf("\n\n");
    printf(RED_BOLD ">>> CONNECTION TERMINATED BY USER\n" RESET);
    printf(RED     ">>> WIPING SESSION LOGS...\n" RESET);
    usleep(600000);
    printf(RED     ">>> DESTROYING EVIDENCE...\n" RESET);
    usleep(600000);
    printf(GREEN_BOLD ">>> SAFE. ALL TRACES REMOVED.\n" RESET);
    usleep(400000);
    printf(RESET "\n");
    exit(0);
}




void slow_print(const char *color, const char *text, int delay_us) {
    printf("%s", color);
    for (int i = 0; text[i]; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        usleep(delay_us);
    }
    printf("\n");
}

void progress_bar(const char *label, int steps, int step_delay_us) {
    printf(GREEN_BOLD "%s [", label);
    fflush(stdout);
    for (int i = 0; i < steps; i++) {
        printf("#");
        fflush(stdout);
        usleep(step_delay_us);
    }
    printf("] DONE\n" RESET);
}

void countdown(const char *prefix, int from, const char *suffix) {
    printf(RED_BOLD "%s ", prefix);
    fflush(stdout);
    for (int i = from; i >= 0; i--) {
        printf("%d... ", i);
        fflush(stdout);
        sleep(1);
    }
    printf("%s\n" RESET, suffix);
}

void fake_ip(void) {
    printf(GREEN "CONNECTING TO %d.%d.%d.%d... OK\n" RESET,
        rand()%255, rand()%255, rand()%255, rand()%255);
}





void boot_sequence(void) {
    printf(GREEN_BOLD);
    printf("╔══════════════════════════════════════════╗\n");
    printf("║       SHADOW NET v2.4 — INITIALIZING     ║\n");
    printf("╚══════════════════════════════════════════╝\n\n");
    printf(RESET);
    usleep(500000);

    slow_print(GREEN, "  LOADING KERNEL MODULES...", 30000);
    usleep(300000);
    progress_bar("  SYSTEM CHECK   ", 20, 60000);
    usleep(300000);

    fake_ip();
    usleep(400000);
    fake_ip();
    usleep(400000);

    slow_print(GREEN_BOLD, "  PROXY CHAIN ESTABLISHED [8 NODES]", 25000);
    usleep(300000);
    progress_bar("  ENCRYPTING SESSION ", 16, 70000);
    usleep(300000);

    slow_print(GREEN_BOLD, "  ROOT ACCESS GRANTED", 40000);
    usleep(500000);

    printf(YELLOW "\n>>> STANDING BY. INITIATING DATA STREAM...\n\n" RESET);
    usleep(800000);
}






int main(void) {
    srand(time(NULL));
    signal(SIGINT, handle_sigint);

    boot_sequence();

    int col = 0;
    int char_count = 0;

    while (1) {
        int event = rand() % 1000;

        // Trace countdown (~every ~2000 chars on average)
        if (event < 1) {
            printf("\n");
            countdown("TRACE DETECTED — DISCONNECTING IN:", 5, "REROUTED!");
            printf("\n");
            col = 0;

        // Red alert message
        } else if (event < 6) {
            printf("\n\n" RED_BOLD "!!! %s !!!\n\n" RESET,
                alert_msgs[rand() % ALERT_COUNT]);
            col = 0;

        // File access
        } else if (event < 14) {
            printf("\n" GREEN "READING %s\n" RESET,
                file_paths[rand() % FILE_COUNT]);
            col = 0;

        // Fake IP connect
        } else if (event < 20) {
            printf("\n");
            fake_ip();
            col = 0;

        // Status message
        } else if (event < 35) {
            printf("\n\n" YELLOW ">>> %s\n\n" GREEN,
                status_msgs[rand() % STATUS_COUNT]);
            col = 0;

        // Hex address line
        } else if (event < 60) {
            printf("\n" GREEN "0x%08X: ", rand());
            col = 12;

        // Normal random char
        } else {
            if (rand() % 4 == 0)
                printf(GREEN_BOLD);
            else
                printf(GREEN);

            printf("%c ", (rand() % 94) + 33);
            col++;
            char_count++;

            if (col >= 40) {
                printf("\n");
                col = 0;
            }
        }

        fflush(stdout);
        usleep((rand() % 30000) + 5000);
    }

    return 0;
}

