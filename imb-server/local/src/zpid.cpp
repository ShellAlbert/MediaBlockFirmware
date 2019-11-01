/**
 * @file zpid.c
 * @brief read/write pid to file
 * @author shell.albert@gmail.com
 */
#include <zpid.h>

/**
 * @brief read parent pid
 */
pid_t
pid_read_from_file (void)
{
  zint32_t fd_lock;
  zint8_t buffer[16];
  zuint32_t pid;

  /**
   * open pid file.
   */
  if ((fd_lock = open (LOCK_PID_FILE_NAME, O_RDONLY)) < 0)
    {
      printf ("error:open %s file failed:%s", LOCK_PID_FILE_NAME,
	      strerror (errno));
      return -1;
    }

  /**
   * read pid.
   */
  memset (buffer, 0, sizeof(buffer));
  if (read (fd_lock, buffer, sizeof(buffer)) < 0)
    {
      printf ("error:null pid in %s\n", LOCK_PID_FILE_NAME);
      return -1;
    }

  pid = strtoul (buffer, 0, 10);
  if (pid == ERANGE)
    {
      printf ("error:strtoul():%s\n", strerror (errno));
      return -1;
    }
  return pid;
}

/**
 * @brief write parent pid to file
 */
zint32_t
pid_write_to_file (zint32_t fd, pid_t pid)
{

  zint8_t buffer[16];

  if (fd < 0)
    {
      return -1;
    }

  /**
   * write pid to file.
   */
  ftruncate (fd, 0);
  memset (buffer, 0, sizeof(buffer));
  sprintf (buffer, "%d", getpid ());
  write (fd, buffer, strlen (buffer));

  return 0;
}

/**
 * @brief lock pid file
 * @return -1:error,fd:success
 */
zint32_t
pid_lock_file (void)
{
  //lock pid
  zint32_t fd_lock;
  struct flock lock;

  /**
   * open file.
   */
  if ((fd_lock = open (LOCK_PID_FILE_NAME, O_RDWR | O_CREAT,
  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) < 0)
    {
      printf ("error:open lock file %s failed:%s\n", LOCK_PID_FILE_NAME,
	      strerror (errno));
      return -1;
    }

#if (ZDBG_LEVEL &ZDBG_PID)
  printf ("info:open pid %s ok\n", LOCK_PID_FILE_NAME);
#endif

  /**
   * try to lock.
   */
  lock.l_type = F_WRLCK; //write lock
  lock.l_start = 0;
  lock.l_whence = SEEK_SET;
  lock.l_len = 0; //lock the whole file
  if (fcntl (fd_lock, F_SETLK, &lock) < 0)
    {
      printf ("error:lock file %s failed:%s", LOCK_PID_FILE_NAME,
	      strerror (errno));
      close (fd_lock);
      return -1;
    }

  /**
   * success here.
   */
  return fd_lock;
}

/**
 * @brief byte order convert
 */
void
int32_to_char8x4 (const uint32_t data_int32, uint8_t *data_char8)
{
  uint8_t tmpdata = 0;

  /**
   * check valid of parameters.
   */
  if (data_char8 == NULL)
    {
      return;
    }
  tmpdata = data_int32 >> 24;
  data_char8[0] = tmpdata;

  tmpdata = data_int32 >> 16;
  data_char8[1] = tmpdata;

  tmpdata = data_int32 >> 8;
  data_char8[2] = tmpdata;

  tmpdata = data_int32 >> 0;
  data_char8[3] = tmpdata;

  return;
}
void
char8x4_to_int32 (const uint8_t *data_char8, uint32_t *data_int32)
{
  uint32_t tmpdata = 0;
  /**
   * check valid of parameters.
   */
  if (data_char8 == NULL || data_int32 == NULL)
    {
      return;
    }
  tmpdata |= data_char8[0];
  tmpdata <<= 24;

  tmpdata |= data_char8[1];
  tmpdata <<= 16;

  tmpdata |= data_char8[2];
  tmpdata <<= 8;

  tmpdata |= data_char8[3];
  tmpdata <<= 0;

  *data_int32 = tmpdata;
  return;
}

/**
 * the end of file,tagged by zsy
 * shell.albert@gmail.com.
 */
